import sys
import os

# -----------------------------------------------------
# Import renderer backend from render_src/main.py
# -----------------------------------------------------
from render_src.main import (
    am_window,
    am_bg,
    am_draw_rect,
    am_wait,
    am_render
)

# -----------------------------------------------------
# Load .anl file from CLI
# -----------------------------------------------------
def load_script_from_cli():
    if len(sys.argv) < 2:
        print("Usage: python antilang.py <file.anl>")
        sys.exit(1)

    path = sys.argv[1]

    if not os.path.exists(path):
        print(f"File not found: {path}")
        sys.exit(1)

    with open(path, "r") as f:
        return f.read()

# -----------------------------------------------------
# Utility: extract values inside (...) and convert types
# -----------------------------------------------------
def extract_args(line):
    inside = line[line.find("(") + 1 : line.rfind(")")]
    parts = [p.strip() for p in inside.split(",") if p.strip()]

    out = []
    for p in parts:
        if p.startswith('"') and p.endswith('"'):
            out.append(p[1:-1])
        elif p.replace(".", "", 1).isdigit():
            # int or float
            if "." in p:
                out.append(float(p))
            else:
                out.append(int(p))
        else:
            out.append(p)
    return out

# -----------------------------------------------------
# EXECUTION FUNCTIONS
# -----------------------------------------------------
def execute_line(line):
    if line.startswith("bg["):
        color = line[3:].split("]")[0]
        am_bg(color)

    elif line.startswith("draw_rect"):
        args = extract_args(line)
        am_draw_rect(*args)

    elif line.startswith("wait"):
        t = extract_args(line)[0]
        am_wait(t)

def eval_window(line):
    args = extract_args(line)
    am_window(args[0], args[1], args[2])

# -----------------------------------------------------
# MAIN INTERPRETER
# -----------------------------------------------------
def run_anilang(code):
    lines = [l.strip() for l in code.split("\n") if l.strip()]

    inner_block = []
    inside_loop = False

    # define dynamic loop function for render(loop)
    def loop_function():
        for ln in inner_block:
            execute_line(ln)

    # parse line-by-line
    for line in lines:
        # window("Test", 600, 500);
        if line.startswith("window"):
            eval_window(line)

        # main loop():
        elif line.startswith("main loop"):
            inside_loop = True

        # render(loop());
        elif line.startswith("render("):
            am_render(loop_function)

        # everything else
        else:
            if inside_loop:
                inner_block.append(line)
            execute_line(line)

# -----------------------------------------------------
# ENTRY POINT
# -----------------------------------------------------
if __name__ == "__main__":
    code = load_script_from_cli()
    run_anilang(code)
