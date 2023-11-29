FROM --platform=linux/amd64 ubuntu
RUN mkdir /app
WORKDIR /app
RUN apt-get update

RUN apt-get install -y wget

RUN apt-get install -y build-essential

RUN apt-get install -y openssh-server vim

RUN apt-get install -y rsync gdb cmake sudo git libfmt-dev libssl-dev

RUN wget -O dpp.deb https://dl.dpp.dev/

RUN apt-get install -y ./dpp.deb

RUN useradd -m -g sudo ubuntu

RUN echo "PermitRootLogin yes" >>/etc/ssh/sshd_config

RUN /etc/init.d/ssh start

CMD ["/bin/bash"]
