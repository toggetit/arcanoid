project(pong)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(src SRC_LIST)


#Проверка наличия SDL
find_package(SDL)
if(${SDL_FOUND})
    link_libraries(${SDL_LIBRARY})
else(${SDL_FOUND})
    MESSAGE(STATUS "Could not locate SDL.")
endif(${SDL_FOUND})

#Проверка наличия SDL__image
find_package(SDL_image)
if(${SDLIMAGE_FOUND})
    link_libraries(${SDL_image_LIBRARY})
else(${SDLIMAGE_FOUND})
    MESSAGE(STATUS "Could not locate SDL_image.")
endif(${SDLIMAGE_FOUND})

set(REQUIRED_LIBRARIES
                SDL)

add_executable(${PROJECT_NAME} ${SRC_LIST})
