set(ROBOSUB_JETSON_SOURCE
	PointAndShoot.cpp
   )
set(ROBOSUB_JETSON_HEADERS
   )
add_subdirectory(Networking)
add_executable(PointAndShoot ${ROBOSUB_JETSON_SOURCE} ${ROBOSUB_JETSON_HEADERS})
