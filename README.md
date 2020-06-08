# hot-wheels

Toy browser engine built with C++11, built for learning a bit about the wizardry that is a browser.

This is extremely stripped back, things like JS are a whole other thing which is out of scope of this project. It probably won't even fetch stuff from the web, just feed in input through args. I might come back and look at this if I enjoy the project.  

**Goals** 

- [x] Parse a subset of HTML
- [x] Parse a subset of CSS attributes
- [x] Arrange elements using blocks
- [x] Paint to a window

## HTML Subset

Syntax can contain 

- Balanced tags e.g. `<title>...</title>`
- Attributes

## Current State

We have paint! We can paint colored rectangles!!!

<img src="docs/rainbowdiv.png" alt="Rainbow colored divs">

## How does a browser engine work? 

The main flow of a browser engine follows a pipe and filter system, HTML and CSS files are fed in as input, parsed and combined to produce a set of requirements for each element on the page, we then calculate the position on screen, producing a render tree which is passed to a painter. 

![Diagram of Pipe and Filter System](docs/webkitflow.png)


## Extenstion Goals

- [ ] Convert CSS parser to use an actual parser generator