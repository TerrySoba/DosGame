# this one is important
SET(CMAKE_SYSTEM_NAME DOS)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   ${CMAKE_CURRENT_LIST_DIR}/../djgpp/bin/i586-pc-msdosdjgpp-gcc)
SET(CMAKE_CXX_COMPILER ${CMAKE_CURRENT_LIST_DIR}/../djgpp/bin/i586-pc-msdosdjgpp-g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../djgpp/)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
