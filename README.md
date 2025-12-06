# AntiLang vAlpha

<p>
  <img src="https://img.shields.io/badge/BUILD-PASSING-brightgreen?style=flat-square">
  <img src="https://img.shields.io/badge/LANGUAGE-Python%20%7C%20C%20%7C%20C++%20%7C%20Fortran-blue?style=flat-square">
  <img src="https://img.shields.io/badge/STATUS-ALPHA-orange?style=flat-square">
</p>

AntiLang is a tiny domain-specific language designed to control the **Antimonic Software Renderer**.  
It reads `.anl` scripts and executes rendering commands through Python bindings that call a C/C++/Fortran backend.

The entire goal is simplicity:

**Write this:**

```anl
window("Demo", 600, 500);
main loop():
    bg[dark_grey];
    draw_rect(100, 100, 64, 64, red);
    wait(0.016);
render(loop());
```

**Get a running software-rendered window.**

---

## 🚀 How It Works

AntiLang uses a lightweight, no-AST interpreter (`antilang.py`) that runs commands _line-by-line_.

Pipeline:

```
script.anl → antilang.py → render_src/main.py → antimonic.dll → pixels on screen
```

- `antilang.py` handles parsing & dispatch
- `render_src/main.py` exposes Python bindings to the renderer
- `antimonic.dll` (or .so / .dylib) is the core renderer in C/C++/Fortran

---

## 📂 Project Structure

```
AntiLang/
│
├── antilang.py           # The interpreter for .anl scripts
├── syntax.anl            # Example language script
│
└── render_src/
    ├── main.py           # Python renderer bindings
    ├── main.c            # Renderer core (C)
    ├── main.cpp          # Renderer core (C++)
    ├── main.f90          # Renderer core (Fortran)
    └── anm.h             # Shared header
```

---

## ▶️ Running AntiLang

Run a `.anl` script:

```
python antilang.py file.anl
```

Example:

```
python antilang.py syntax.anl
```

---

## 🧩 Language Syntax (AntiLang DSL)

### Window creation

```anl
window("Title", width, height);
```

### Render loop

```anl
main loop():
    ...
render(loop());
```

### Commands inside loop

```anl
bg[color];
draw_rect(x, y, w, h, color);
wait(seconds);
```

---

## 🛠️ Build Antimonic Renderer

The renderer lives in `render_src/` and can be compiled from:

- `main.c`
- `main.cpp`
- `main.f90`

Output must be named:

```
antimonic.dll  (Windows)
antimonic.so   (Linux)
antimonic.dylib (macOS)
```

Place the compiled binary in:

```
Trappist/Antimonic/
```

Update the path in `render_src/main.py` if needed.

---

## 📌 Goals (Alpha)

- Lightweight scripting language for 2D rendering
- Small, clean interpreter
- Cross-language renderer backend
- Simple DSL for beginners & fast prototyping

---

## 📜 License

Under MIT so do whatever you want!

---

## 🌍 Portability

AntiLang and the Antimonic Renderer are built to run anywhere you can boot a computer.  
The backend speaks **C, C++ and Fortran**, giving it strong cross-platform muscles with a tiny setup footprint.

### 🚦 Supported Platforms

AntiLang runs smoothly across all major OSes:

- **Windows** → `antimonic.dll`
- **Linux** → `libantimonic.so`
- **macOS** → `libantimonic.dylib`

The Python interpreter (`antilang.py`) stays identical across platforms — it just loads the correct shared library and gets to work.

---

## 🔧 Cross-Language Backend Layout

The renderer backend is built from a compact and efficient set of sources:

- `main.c` — core API
- `main.cpp` — extended features
- `main.f90` — numeric + compute routines
- `anm.h` — shared header

Each language plays its part like a well-behaved multi-language orchestra.

### 🧰 Compilers Used

To keep portability predictable and drama-free:

- **C:** gcc / clang
- **C++:** g++ / clang++
- **Fortran:** gfortran

If your system has these, it can run Antimonic.

---

## 📦 Shared Library Behavior

The Python renderer (`render_src/main.py`) automatically loads the correct shared library depending on your OS.

Only _one_ file is needed at runtime:

```sh
Windows     # antimonic.dll
Linux       # libantimonic.so
macOS       # libantimonic.dylib
```

You can place the file anywhere — just update the path in `main.py`.  
Or keep things tidy inside a folder like:

```sh
Antimonic/
```

---

## 🧠 Interpreter Independence

The AntiLang interpreter avoids OS-specific features. It relies on:

- pure Python file I/O
- simple string parsing
- runtime operator dispatch to the renderer

This means the language itself is portable even without a rebuild, as long as a renderer library exists for the current OS.

---

## ⚡ Porting TL;DR

- Compile the renderer backend for the new platform
- Grab the `.dll`, `.so`, or `.dylib` output
- Put it somewhere Python can load it
- Run your script:

```sh
python antilang.py script.anl
```

That’s it — no weird setup, no arcane configs, no “why does this only work on my machine” energy.

---
