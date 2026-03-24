# Docker {#docker}

## Fetch the environment

1. Make sure you have the rights to pull the docker image 

2. Pull the docker image

```
docker pull ghcr.io/variton/icxx-resolute:1.0

```

## Run the container

1. Go to the xcurl-wpr directory

2. Launch the container

create the docker container

```
docker run --name=cxx-resolute --hostname=cypher -v $PWD:/home/cxx-core --net=host --restart=no -it icxx-resolute:1.0 /bin/bash

```
