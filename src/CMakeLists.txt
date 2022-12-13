cmake_minimum_required(VERSION 3.0)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

project(List C)
# add_executable(rb-tree rb-tree.c rb-tree.h)
add_library(rb-tree SHARED rb-tree.c rb-tree.h)

install(
	TARGETS rb-tree
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
)

install(
	FILES rb-tree.h
	DESTINATION include
)

# Ajout d'un fichier de configuration de type pkgconfig. Copie le 1er argument vers le 2ème. @ONLY = restreint le remplacement de variable dans rb-tree.pc.in
# à celles qui ont le format @<var>@ pour éviter les conflits avec la syntaxe CMake ${<var>}.
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/rb-tree.pc.in
	${CMAKE_CURRENT_BI_DIR}/rb-tree.pc
	@ONLY
)
install(
	FILES ${CMAKE_CURRENT_BI_DIR}/rb-tree.pc
	DESTINATION share/pkgconfig
	COMPONENT "PkgConfig"
)

#  Ajout d'un fichier de configuration de type cmake
include(CMakePackageConfigHelpers)
configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/RBTreeConfig.cmake.in
	${CMAKE_CURRENT_BI_DIR}/RBTreeConfig.cmake
	INSTALL_DESTINATION cmake
)
install(
	FILES ${CMAKE_CURRENT_BI_DIR}/RBTreeConfig.cmake
	DESTINATION cmake
)

# Ajout d'un exécutable dépendant également de rb-tree.h
add_executable(test-rb-tree test-rb-tree.c rb-tree.h)
# Précision de l'ordre de construction: le programme de test doit se faire
# après la librairie
add_dependencies(test-rb-tree rb-tree)
# Aggrégation du programme de test avec la librairie rb-tree
target_link_libraries(test-rb-tree rb-tree m)

# Activation des tests
enable_testing()
# Ajout d'un test
add_test(test-rb-tree ./test-rb-tree)
