# Tataru helper linux cli analog

## Requirements

Process: Xorg screenshot -> openCV -> ggl translate

for screenshot: X11, Xext
for preprocessing img: opencv4
for OCR: tesseract with installed lang libraries (from and to)
for get-request to translate: cpr (curl wrapper)
for loading yaml-config: yaml-cpp
for compile: clang

## Usage

run ./bin/tataru with path to your .yaml config:
`/home/user/tataru-ocr/bin/tataru "/home/user/tataru-ocr/CONFIG.yaml"`
