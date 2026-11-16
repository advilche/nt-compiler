# NT compiler
NT is a hand-written single pass, ahead of time compiler in C. It will soon make use of a recursive-descent parser. It has started with a very small C subset, currently in tokenizing phase. For example...

```c
return 21;
```

```bash
Type: keyword
Text: return
Length: 6

Type: constant
Text: 21
Length: 2

Type: special
Text: ;
Length: 1
```
## Usage

```bash
./lexer main.c 
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)