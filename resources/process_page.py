from pathlib import Path

output = Path("src/webpage.h")

file_content = ""
with Path("resources/page.html").open("r") as f:
    for line in f.readlines():
        file_content += line.strip().replace('"', "'")
print(file_content)
with Path(output).open("w") as f:
    f.write('const char index_html[] PROGMEM = "')
    f.write(file_content)
    f.write('";')
