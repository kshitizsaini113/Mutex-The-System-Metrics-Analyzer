FROM centos
RUN yum update -y
RUN dnf install gcc-c++ -y
RUN dnf install ncurses-devel -y
RUN mkdir /mutex
RUN mkdir /preudoproc
RUN mkdir /pseudoetc
COPY ./src /mutex
RUN c++ ./src/main.cpp -o /usr/bin/mutex
RUN rm -rvf /mutex