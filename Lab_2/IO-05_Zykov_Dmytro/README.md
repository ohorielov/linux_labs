
### Building
---
#### Release build
Applies all optimization, doesn't test correctness of compression.
```
make
```
#### Debug build
While compressing decodes encoded data and ensures that it matches the original.
```
make debug
```

### Usage
---
```
./huffman <input file> <output file> [-c|-d]
```
-c - compresses the file

-d - decompresses the file