#### Build project:
    docker build -t cppbox . 

#### Run container:
    docker run -ti -p 8888:8888 -e PORT=8888 cppbox:latest bash

#### Find and run test application:
    cd /usr/src/ShareCreation/tests/build
    ./tunTests

#### Find and run aplication:
    cd /usr/src/ShareCreation/npu_backend/build
    ./npu_backend

#### Quick API integration test with curl

    curl localhost:8888

    curl -X POST http://localhost:8888/login -H "Content-Type: application/json" -d '{"username":"admin", "password":"password"}'
