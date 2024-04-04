DOCKER_IMAGE_NAME = dats_eden_space
DATA_DIR = $(CURDIR)/data

all: build run

build:
	docker build -t $(DOCKER_IMAGE_NAME) .

run:
	docker run --rm -v $(DATA_DIR):/app/data $(DOCKER_IMAGE_NAME)

.PHONY: build run
