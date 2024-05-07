FROM debian:11

RUN apt-get update &&\
		apt-get install -y gcc git libreadline-dev make

RUN git clone https://github.com/rchanrenous/42_projects
WORKDIR 42_projects/philosophers
#RUN make && make clean

CMD ["sleep", "infinity"]
