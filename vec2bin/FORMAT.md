# CVEC Binary Format Specification

This document describes the `.cvec` binary format used by Cmantix to store word embeddings.

## Overview

The CVEC format stores word vectors in a binary format optimized for fast loading.
It is generated from FastText/Word2Vec `.vec` text files.

```
┌─────────────────────────────────────────────────────────┐
│                      HEADER (16 bytes)                  │
├─────────────────────────────────────────────────────────┤
│              WORD INDEX TABLE (12 bytes × N)            │
├─────────────────────────────────────────────────────────┤
│                STRING POOL (variable size)              │
├─────────────────────────────────────────────────────────┤
│              VECTOR DATA (1200 bytes × N)               │
└─────────────────────────────────────────────────────────┘
```

All multi-byte integers are stored in **little-endian** format.

---

## Section 1: Header

Fixed size: **16 bytes**

| Offset | Size | Type     | Field       | Description                          |
|--------|------|----------|-------------|--------------------------------------|
| 0      | 4    | char[4]  | magic       | Magic number: "CVEC" (0x43455643)    |
| 4      | 4    | uint32   | version     | Format version (currently 1)         |
| 8      | 4    | uint32   | num_words   | Total number of words in the file    |
| 12     | 4    | uint32   | dimensions  | Vector dimensions (typically 300)    |

The magic number allows quick validation that a file is in CVEC format.

---

## Section 2: Word Index Table

Fixed size per entry: **12 bytes**
Total size: **12 × num_words bytes**

Each entry describes one word:

| Offset | Size | Type   | Field         | Description                              |
|--------|------|--------|---------------|------------------------------------------|
| 0      | 4    | uint32 | string_offset | Byte offset into the string pool         |
| 4      | 4    | uint32 | string_length | Length of the word string (no null term) |
| 8      | 4    | uint32 | vector_index  | Index into the vector data section       |

Entries are stored in the same order as they appear in the source `.vec` file
(typically sorted by word frequency, most common first).

---

## Section 3: String Pool

Variable size: sum of all word string lengths.

All word strings are concatenated without null terminators or separators.
Use `string_offset` and `string_length` from the index table to extract words.

Example for words "chat", "chien", "maison":
```
Offset 0:  c h a t c h i e n m a i s o n
           |-------|---------|-----------|
           chat    chien     maison
           len=4   len=5     len=6
```

---

## Section 4: Vector Data

Fixed size per vector: **dimensions × 4 bytes** (1200 bytes for 300 dimensions)
Total size: **dimensions × 4 × num_words bytes**

Vectors are stored as arrays of `float32` values, contiguous in memory.
The `vector_index` field from the index table gives the position.

To get the byte offset of vector N:
```
vector_offset = header_size + index_table_size + string_pool_size + (N × dimensions × 4)
```

---

## Calculating Section Offsets

| Section      | Start Offset                                    |
|--------------|-------------------------------------------------|
| Header       | 0                                               |
| Index Table  | 16                                              |
| String Pool  | 16 + (12 × num_words)                           |
| Vector Data  | 16 + (12 × num_words) + string_pool_size        |

The string pool size must be calculated by summing all `string_length` values,
or by reading all strings from the source file first.

---

## Example

A file with 3 words: "chat" (4), "chien" (5), "maison" (6)

### Header (16 bytes)
```
00000000: 43 56 45 43  magic = "CVEC"
00000004: 01 00 00 00  version = 1
00000008: 03 00 00 00  num_words = 3
0000000C: 2C 01 00 00  dimensions = 300
```

### Index Table (36 bytes)
```
00000010: 00 00 00 00 04 00 00 00 00 00 00 00  "chat":   offset=0,  len=4, vec=0
0000001C: 04 00 00 00 05 00 00 00 01 00 00 00  "chien":  offset=4,  len=5, vec=1
00000028: 09 00 00 00 06 00 00 00 02 00 00 00  "maison": offset=9,  len=6, vec=2
```

### String Pool (15 bytes)
```
00000034: 63 68 61 74 63 68 69 65 6E 6D 61 69 73 6F 6E
          c  h  a  t  c  h  i  e  n  m  a  i  s  o  n
```

### Vector Data (3600 bytes)
```
00000043: [300 × float32 for "chat"  ]
00000497: [300 × float32 for "chien" ]
000008EB: [300 × float32 for "maison"]
```

---

## Usage

### Generating a .cvec file

```bash
./vec2bin data/cc.fr.50k.vec data/french.cvec
```

### Loading in Cmantix

1. Open file, read and validate header
2. Read index table into memory
3. Read string pool into memory
4. Read vector data into memory (or mmap)
5. Build hash table: word → vector pointer

---

## Versioning

The `version` field allows for future format changes while maintaining
backwards compatibility. Current version: **1**.
