# Diff Details

Date : 2022-10-10 07:38:55

Directory /home/plato/mipt_projs/course2/graphic_lib/src

Total : 40 files,  427 codes, 48 comments, 189 blanks, all 664 lines

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/GraphicEditor.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/GraphicEditor.cpp) | C++ | -73 | -10 | -35 | -118 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/Raytracer.h](//home/plato/mipt_projs/course2/geometry_simulator/src/Raytracer.h) | C++ | -107 | -8 | -41 | -156 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/geom_primitives/Plane.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/geom_primitives/Plane.cpp) | C++ | -40 | -8 | -22 | -70 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/geom_primitives/Sphere.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/geom_primitives/Sphere.cpp) | C++ | -59 | -5 | -24 | -88 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/geom_primitives/Vector.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/geom_primitives/Vector.cpp) | C++ | -84 | -15 | -44 | -143 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/geom_primitives/Vector3D.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/geom_primitives/Vector3D.cpp) | C++ | -84 | -17 | -41 | -142 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/geometry_objects.h](//home/plato/mipt_projs/course2/geometry_simulator/src/geometry_objects.h) | C++ | -99 | -3 | -44 | -146 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/graphic_lib_wrapper.h](//home/plato/mipt_projs/course2/geometry_simulator/src/graphic_lib_wrapper.h) | C++ | -158 | -17 | -52 | -227 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/graphical_primitives/Button.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/graphical_primitives/Button.cpp) | C++ | -32 | -5 | -13 | -50 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/graphical_primitives/Color.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/graphical_primitives/Color.cpp) | C++ | -65 | -8 | -32 | -105 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/graphical_primitives/CoordinateSys.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/graphical_primitives/CoordinateSys.cpp) | C++ | -84 | -9 | -37 | -130 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/graphical_primitives/Text.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/graphical_primitives/Text.cpp) | C++ | -18 | -3 | -13 | -34 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/graphical_primitives/Vector.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/graphical_primitives/Vector.cpp) | C++ | -62 | -16 | -39 | -117 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/main.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/main.cpp) | C++ | -19 | -2 | -6 | -27 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/tests.h](//home/plato/mipt_projs/course2/geometry_simulator/src/tests.h) | C++ | -29 | -2 | -12 | -43 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/tests/ActionVectorsTest.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/tests/ActionVectorsTest.cpp) | C++ | -65 | -10 | -30 | -105 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/tests/RaytracingTest.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/tests/RaytracingTest.cpp) | C++ | -207 | -66 | -94 | -367 |
| [/home/plato/mipt_projs/course2/geometry_simulator/src/tests/SphereTest.cpp](//home/plato/mipt_projs/course2/geometry_simulator/src/tests/SphereTest.cpp) | C++ | -90 | -13 | -41 | -144 |
| [GraphicEditor.cpp](/GraphicEditor.cpp) | C++ | 73 | 10 | 35 | 118 |
| [Raytracer.h](/Raytracer.h) | C++ | 20 | 1 | 11 | 32 |
| [dts.h](/dts.h) | C++ | 194 | 33 | 80 | 307 |
| [geom_primitives/Plane.cpp](/geom_primitives/Plane.cpp) | C++ | 39 | 8 | 21 | 68 |
| [geom_primitives/Sphere.cpp](/geom_primitives/Sphere.cpp) | C++ | 59 | 5 | 24 | 88 |
| [geom_primitives/Vector.cpp](/geom_primitives/Vector.cpp) | C++ | 87 | 16 | 45 | 148 |
| [geom_primitives/Vector3D.cpp](/geom_primitives/Vector3D.cpp) | C++ | 87 | 18 | 42 | 147 |
| [geometry_objects.h](/geometry_objects.h) | C++ | 102 | 3 | 46 | 151 |
| [graphic_lib_wrapper.h](/graphic_lib_wrapper.h) | C++ | 157 | 17 | 52 | 226 |
| [graphical_primitives/Button.cpp](/graphical_primitives/Button.cpp) | C++ | 36 | 3 | 14 | 53 |
| [graphical_primitives/Color.cpp](/graphical_primitives/Color.cpp) | C++ | 63 | 8 | 31 | 102 |
| [graphical_primitives/CoordinateSys.cpp](/graphical_primitives/CoordinateSys.cpp) | C++ | 84 | 9 | 38 | 131 |
| [graphical_primitives/Text.cpp](/graphical_primitives/Text.cpp) | C++ | 15 | 3 | 11 | 29 |
| [graphical_primitives/Vector.cpp](/graphical_primitives/Vector.cpp) | C++ | 62 | 14 | 39 | 115 |
| [logger.cpp](/logger.cpp) | C++ | 161 | 19 | 88 | 268 |
| [logger.h](/logger.h) | C++ | 68 | 19 | 24 | 111 |
| [main.cpp](/main.cpp) | C++ | 19 | 2 | 6 | 27 |
| [scene_objects.h](/scene_objects.h) | C++ | 105 | 6 | 35 | 146 |
| [tests.h](/tests.h) | C++ | 29 | 2 | 12 | 43 |
| [tests/ActionVectorsTest.cpp](/tests/ActionVectorsTest.cpp) | C++ | 65 | 9 | 30 | 104 |
| [tests/RaytracingTest.cpp](/tests/RaytracingTest.cpp) | C++ | 187 | 50 | 83 | 320 |
| [tests/SphereTest.cpp](/tests/SphereTest.cpp) | C++ | 90 | 10 | 42 | 142 |

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details