set(ROBOSUB_JETSON_SOURCE
    ${ROBOSUB_JETSON_SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/M2NStandardPacket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/N2MStandardPacket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkLogger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkServer.cpp
    PARENT_SCOPE
   )
set(ROBOSUB_JETSON_HEADERS
    ${ROBOSUB_JETSON_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/M2NStandardPacket.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/N2MStandardPacket.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkLogger.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkServer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Packet.hpp
    PARENT_SCOPE
   )
