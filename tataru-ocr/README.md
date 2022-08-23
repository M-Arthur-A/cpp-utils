# Tataru helper linux cli analog
beta version

## Requirements
for screenshot: X11, Xext
for preprocessing img: opencv4
for OCR:tesseract with lang_libraries (from and to)
for get-request to translate: cpr (curl wrapper)
for loading yaml-config: yaml-cpp
for compile: clang

## Usage
run ./bin/tataru with path to your .yaml config:
`/home/user/tataru-ocr/bin/tataru "/home/user/tataru-ocr/CONFIG.yaml"`

## How it works
Xorg screenshot -> openCV -> ggl translate
