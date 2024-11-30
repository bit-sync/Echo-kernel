# Display Namespace Documentation

The `display` namespace provides low-level screen manipulation functions for text-mode display output. It interfaces directly with video memory at address `0xb8000` and provides basic text output functionality with color support.

## Screen Specifications
- Screen dimensions: 25 lines × 80 columns
- Each screen element consists of 2 bytes:
  - First byte: ASCII character
  - Second byte: Attribute byte (text color and background color)
- Total screen size: 4000 bytes (25 × 80 × 2)

## Color Constants

The following color constants are available for text formatting:

| Constant | Value | Description |
|----------|-------|-------------|
| `CL_BLACK` | 0x00 | Black |
| `CL_BLUE` | 0x01 | Blue |
| `CL_GREEN` | 0x02 | Green |
| `CL_CYAN` | 0x03 | Cyan |
| `CL_RED` | 0x04 | Red |
| `CL_MAGENTA` | 0x05 | Magenta |
| `CL_BROWN` | 0x06 | Brown |
| `CL_LIGHT_GREY` | 0x07 | Light Grey (Default) |
| `CL_DARK_GREY` | 0x08 | Dark Grey |
| `CL_LIGHT_BLUE` | 0x09 | Light Blue |
| `CL_LIGHT_GREEN` | 0x0A | Light Green |
| `CL_LIGHT_CYAN` | 0x0B | Light Cyan |
| `CL_LIGHT_RED` | 0x0C | Light Red |
| `CL_LIGHT_MAGENTA` | 0x0D | Light Magenta |
| `CL_YELLOW` | 0x0E | Yellow |
| `CL_WHITE` | 0x0F | White |

## Functions

### `void clear_screen(void)`
Clears the entire screen by filling it with spaces and setting the default color attribute (light grey on black).

### `void print(const char *str)`
Prints a null-terminated string to the screen using the default color (light grey on black).

**Parameters:**
- `str`: Null-terminated string to print. If NULL, the function returns without doing anything.

**Features:**
- Handles newline characters (`\n`)
- Automatically scrolls when reaching the bottom of the screen
- Stops printing if screen buffer is full

### `void printc(const char *str, unsigned char color)`
Prints a null-terminated string to the screen using the specified color attribute.

**Parameters:**
- `str`: Null-terminated string to print. If NULL, the function returns without doing anything.
- `color`: Color attribute byte specifying text and background colors

**Features:**
- Same as `print()`, but with custom color support
- Use color constants defined above for the `color` parameter

### `void print_newline(void)`
Moves the cursor to the beginning of the next line.

**Features:**
- Automatically scrolls the screen up when reaching the bottom
- Clears the new line at the bottom after scrolling

### `void backspace(void)`
Removes the character before the current cursor position.

**Features:**
- Moves cursor back one position
- Clears the character at that position
- Only operates if there is space to move back (cursor position >= 2)

## Implementation Details

- Video memory is accessed directly at address `0xb8000`
- Screen content is managed using a linear buffer where each character occupies 2 bytes
- The namespace maintains a static cursor position (`current_loc`) for tracking where the next character will be written
- Scrolling is implemented by moving all lines up one position and clearing the bottom line
