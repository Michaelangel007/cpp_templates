# Generic Template vs Partial Template Specialization

Generic Array<bool>

```
Generic Template: char
Elements: 4096,  Element Size: 1,  Array Size: 4096

Generic Template: bool
Elements: 4096,  Element Size: 1,  Array Size: 4096
```

vs.

Partial Template Specialization Array<bool>

```
Generic Template: char
Elements: 4096,  Element Size: 1,  Array Size: 4096

Partial Template Specialization: bool
Elements: 512,  Element Size: 1,  Array Size: 512
Saved bytes: 3584
```

