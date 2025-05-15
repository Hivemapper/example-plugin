# Example Plugin

The Example Plugin is a C++ application designed to interact with specific REST API endpoints. It includes Docker support so you can easily run it in an isolated environment and, if needed, enable a test mode that starts a mock HTTP server returning preset JSON responses.

## Features

- **Build with CMake and Make:** Easily compile your C++ code.
- **Dockerized Environment:** Run your application inside a Docker container.
- **Test Mode:** Spin up a Python-based Flask test server that simulates API endpoints.
- **Run-Time Configuration:** Dynamically configure API endpoints using environment variables.

## Prerequisites

- [Docker](https://docs.docker.com/get-docker/) installed on your machine.
- Basic knowledge of Docker command-line usage is helpful.

## Docker Setup and Build Instructions

### 1. Build the Docker Image

Open a terminal in your repository directory and run:

```bash
docker build -t example-plugin .
```

This command will:

- Pull the Ubuntu 20.04 base image.
- Install required packages (`cmake`, `build-essential`, `libeigen3-dev`, `libcurl4-openssl-dev`, `python3`, `pip3`, and optionally `netcat` if you opt for a connectivity check).
- Copy your repository files into the container.
- Build the C++ application using CMake and Make.
- Set up the container entrypoint that conditionally starts the test server in test mode.

### 2. Running the Docker Container

#### Production Mode

Production Mode requires your local machine to be connected to WiFi network of Bee device.
Once connected,
to run the container in normal (production) mode, execute:

```bash
docker run --rm example-plugin
```

The application will use default environment variables for its API endpoints.

#### Test Mode

Test mode starts an embedded Python Flask test server that mocks your API endpoints. The test server is launched in the background, and the C++ application requests data from it.

> **Note:** When running in test mode, the `entrypoint.sh` script overrides the API endpoint environment variables.

To run in test mode, execute:

```bash
docker run --rm -e TEST_MODE=1 -p <HOST_PORT>:9000 example-plugin
```

Replace `<HOST_PORT>` with an available port on your host (for example, `9001` if `9000` is in use). For example:

```bash
docker run --rm -e TEST_MODE=1 -p 9001:9000 example-plugin
```

This command does the following:

- Sets `TEST_MODE=1` in the container.
- The `entrypoint.sh` script detects test mode and sets:
  - `DASHCAM_HOST` to `127.0.0.1`
  - `DASHCAM_PORT` to `9000`
- The test server starts and listens on port `9000` inside the container.
- With `-p <HOST_PORT>:9000`, you can access the test server from your host on `<HOST_PORT>`.

### 3. Debugging Tips

#### Check Running Containers

Use:

```bash
docker ps
```

to list all running containers.

#### View Container Logs

If the container exits quickly, remove the `--rm` flag and run:

```bash
docker logs <container_id>
```

Replace `<container_id>` with the actual ID retrieved from `docker ps -a`.

#### Interactive Shell

To inspect the container’s state, you can override the entrypoint temporarily:

```bash
docker run -it --entrypoint bash example-plugin
```

The python test server and plugin will not run automatically with this command. You will need to run them manually

```bash
root@9857a99e67b0:/usr/src/app# TEST_MODE=1 bash entrypoint.sh
```

#### Test the Server Manually

Inside the container (or from your host if ports are mapped), run:

```bash
curl http://127.0.0.1:<HOST_PORT>/api/1/landmarks/latest
```

to verify the test server is responding.

## Environment Variables

The application uses the following environment variables to construct the API endpoint URLs dynamically:

- `DASHCAM_HOST` (default: `192.168.0.10`)
- `DASHCAM_PORT` (default: `5000`)

When running in test mode, the entrypoint script sets:

- `DASHCAM_HOST` to `127.0.0.1`
- `DASHCAM_PORT` to `9000`

You can override these by passing additional `-e` options to the Docker run command.

## Additional Information

The `entrypoint.sh` script:

- Starts the test server (when `TEST_MODE` is set).
- Waits (using a delay or a readiness check) until the test server is responsive.
- Launches the main C++ application.

The `test_server.py` script (built using Flask) provides the following endpoints:

- `GET /api/1/landmarks/latest`: Returns the latest landmark.
- `GET /api/1/landmarks/last/<n>`: Returns the last `n` landmarks.
- `GET /api/1/landmarks`: Returns filtered landmarks with optional query parameters: since and until (unix timestamps)
- `GET /api/1/landmarks/id/<id>`: Returns landmarks starting with a given ID.
- `GET /api/1/info/`: Returns general info data.

## Docker Cross-compile Option

Cross compilation for aarch64 can be performed by building within a docker image and then copying the executable over onto the Bee dashcam manually.

1. Compile by running the script `/example-plugin/cross-compile/docker_cross_compile.sh`. This scipt will copy the executable into the local directory as `/example-plugin/cross-compile/ExamplePlugin`.
2. Copy the `ExamplePlugin` executable created by the docker container onto the dashcam with `scp`. E.g. `scp -o StrictHostKeyChecking=no /example-plugin/cross-compile/ExamplePlugin root@192.168.0.10:/data/`
3. ssh onto the dashcam and run the executable manually: `./data/ExamplePlugin`
