g++ -pthread -O3 -DNDEBUG -I /home/user/openvdb -I /home/user/ -isystem /opt/houdini/toolkit/include -isystem /rel/folio/log4cplus/log4cplus-1.0.3-latest/sys_include -DOPENVDB_USE_BLOSC -DOPENVDB_USE_LOG4CPLUS -DOPENVDB_USE_GLFW_3 -o openvdb_hello_world openvdb_hello_world.cpp -L/home/user/openvdb /home/user/openvdb/libopenvdb.so.3.1.0 -ldl -lm -lz -Wl,-rpath,/opt/houdini/dsolib -L/opt/houdini/dsolib -lHalf -ltbb -lboost_iostreams -lboost_system -lblosc -Wl,-rpath,/rel/folio/log4cplus/log4cplus-1.0.3-latest/library -L/rel/folio/log4cplus/log4cplus-1.0.3-latest/library -llog4cplus -lrt -ljemalloc
