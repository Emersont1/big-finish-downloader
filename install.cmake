set(APP_LOW_NAME "big finish downloader")
set(APP_VERSION ${PROJECT_VERSION})
set(APP_NAME "Big Finish Dowloader")
set(APP_URL "https://github.com/Emersont1/big-finish-downloader")


install(DIRECTORY ${CMAKE_BINARY_DIR}/bin DESTINATION /   )
install(DIRECTORY ${CMAKE_BINARY_DIR}/lib DESTINATION /   )
install(DIRECTORY ${CMAKE_BINARY_DIR}/share DESTINATION / )

if(WIN32)
  set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} ${CMAKE_MODULE_PATH})

  # download theme
  if(NOT EXISTS ${CMAKE_BINARY_DIR}/content.zip)
  file(DOWNLOAD https://github.com/Emersont1/win-gtk-base/archive/v4.zip ${CMAKE_BINARY_DIR}/content.zip)
  endif()
  file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/content.zip DESTINATION ${CMAKE_BINARY_DIR}/content)
  file(MAKE_DIRECTORY ${directory}${CMAKE_BINARY_DIR}/share)
  file(COPY ${CMAKE_BINARY_DIR}/content/win-gtk-base-4/share DESTINATION ${CMAKE_BINARY_DIR} FOLLOW_SYMLINK_CHAIN)

  set(CPACK_GENERATOR NSIS)
  set(CPACK_PACKAGE_NAME "Big Finish Downloader")
  set(CPACK_PACKAGE_VENDOR "CMake.org")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Big Finish Downloader")
  set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "Big Finish Downloader")
  # I give up with the icons
  set(CPACK_PACKAGE_ICON ${CMAKE_SOURCE_DIR}\\\\icons\\\\tardiswide.bmp)
  set(CPACK_NSIS_INSTALLED_ICON_NAME bin\\\\big-finish-downloader-gtk.exe)
  set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENCE)

  set(CPACK_NSIS_MENU_LINKS  bin\\\\big-finish-downloader-gtk.exe "Big Finish Downloader")

set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
  CreateShortCut \\\"$DESKTOP\\\\Big Finish Downloader.lnk\\\" \\\"$INSTDIR\\\\bin\\\\big-finish-downloader-gtk.exe\\\"
")

set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
  Delete \\\"$DESKTOP\\\\Big Finish Downloader.lnk\\\"
")
  #SET(CPACK_NSIS_MODIFY_PATH ON)
  
  INCLUDE(CPack)
endif()