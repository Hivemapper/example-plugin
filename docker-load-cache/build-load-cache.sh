docker run --rm --privileged tonistiigi/binfmt --install all
docker buildx create --use --name mybuilder
docker buildx inspect --bootstrap
docker buildx build --progress=plain --platform linux/arm64 -t load-cache --build-arg CACHE_ARCHIVE=collection_2024050356.tar.gz --load .
docker run --platform linux/arm64 -it load-cache
