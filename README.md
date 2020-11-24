# RD-88 Sounds manager
The Roland RD-88 stage piano comes with more than 3500 tones and 400 pre-built scenes. A scene can have up to 3 tones but I was not able to find these dependencies listed in any Roland documentation. So it is very difficult to know if a tone is used in any scene, which scenes use which tones and what scenes exist on an backup file.

This tool is a personal project to try to make it easier to manage scenes, tones and backup files by providing tools to get an overview of sounds and their dependencies and to find tones and scenes related to a particular sound category

This tool only can open SVD files from the RD-88 keyboard.

**License**: MIT License 

### Features:
I have just started the research to try to understand the SVD file format, so for now the tool:
* Lists the scenes contained in an SVD file, providing info about the tones composing each scene.
* Lists all standard tones included in a factory new RD-88 keyboard

A spreadsheet with all standard tones in a factory new RD-88 keyboard is also included in 'sounds' folder.

