from pathlib import Path

for i in range(1, 73):
    Path(f'pages/{i:03d}.txt').touch()
