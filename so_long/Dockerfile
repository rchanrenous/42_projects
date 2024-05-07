FROM debian:11

RUN apt-get update &&\
		apt-get install -y gcc git make xorg libxext-dev libbsd-dev

RUN git clone https://github.com/rchanrenous/42_projects
WORKDIR 42_projects/so_long
RUN make && make clean

CMD ["sleep", "infinity"]
