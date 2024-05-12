FROM debian:11

RUN apt-get update &&\
		apt-get install -y gcc git make

RUN git clone https://github.com/rchanrenous/42_projects
WORKDIR 42_projects/push_swap
RUN make bonus && make clean

CMD ["sleep", "infinity"]
