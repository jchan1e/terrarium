let b:syntastic_cpp_cflags=' -std=c++11 -Wno-deprecated -Wno-c++11-extensions $(sdl2-config --cflags) -DGL_GLEXT_PROTOTYPES'
let b:syntastic_c_cflags='-Wno-deprecated'

set ts=4
set shiftwidth=4
imap fj <esc>
