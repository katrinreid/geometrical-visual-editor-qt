set(PROJECT_LIBRARY
        include/paint/mode_enum.hpp
        include/paint/palette_button.hpp
        include/paint/figure.hpp
        include/paint/figure_file_manager.hpp
        include/paint/canvas.hpp
        include/paint/paint_app.hpp
        paint_app.cpp
        palette_button.cpp
        figure_file_manager.cpp
        figure.cpp
        canvas.cpp)

add_library(paint STATIC
        ${PROJECT_LIBRARY})

target_include_directories(paint PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

target_link_libraries(paint PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
install(TARGETS paint)