cmake_minimum_required(VERSION 3.6.0)
project(Leaf)
include_directories(
	${PROJECT_SOURCE_DIR}/Leaf-chat/include
	${PROJECT_SOURCE_DIR}Leaf-chat/src
	${PROJECT_SOURCE_DIR}/Leaf-chat/Network/include
	${PROJECT_SOURCE_DIR}Leaf-chat/Network/src
)
file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/Leaf-chat/include/*"
	"${PROJECT_SOURCE_DIR}/Leaf-chat/src/*"
	"${PROJECT_SOURCE_DIR}/Leaf-chat/Network/include/*"
	"${PROJECT_SOURCE_DIR}Leaf-chat/Network/src/*"
	"${PROJECT_SOURCE_DIR}/*"
)
add_executable(Leaf ${SRCS})
find_package(SDL2 REQUIRED)
target_link_libraries(Leaf ${SDL2_LIBRARIES})
find_package(SDL2_image REQUIRED)
target_link_libraries(Leaf ${SDL2_IMAGE_LIBRARIES})
find_package(SDL2_ttf REQUIRED)
target_link_libraries(Leaf ${SDL2_TTF_LIBRARIES})
find_package(SDL2_net REQUIRED)
target_link_libraries(Leaf ${SDL2_NET_LIBRARIES})