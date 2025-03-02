docker build -t cppbox . 

cd /usr/src/cppweb/npu_backend/build
cmake ..
make

docker run -v .:/usr/src/cppweb -ti -p 8888:8888 -e PORT=8888 cppbox:latest bash

curl localhost:8888
curl -X POST http://localhost:8888/login -H "Content-Type: application/json" -d '{"username":"admin", "password":"password"}'