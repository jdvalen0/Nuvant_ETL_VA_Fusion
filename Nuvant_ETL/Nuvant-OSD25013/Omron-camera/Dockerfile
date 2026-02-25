# Use the official Python 3.7 image as the base
FROM ubuntu:18.04

# Set the working directory
WORKDIR /scripts
RUN apt update && apt upgrade -y
RUN apt install -y software-properties-common build-essential libssl-dev zlib1g-dev libncurses5-dev libgdbm-dev \
libnss3-dev libsqlite3-dev libreadline-dev libffi-dev curl wget
RUN add-apt-repository ppa:deadsnakes/ppa
RUN apt update
RUN apt install -y python3.7
RUN update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.7 1
RUN update-alternatives --config python3
RUN apt install -y python3-pip
RUN mkdir -p /etc/udev/rules.d

COPY SentechSDK-1.1.2-Update5-Ubuntu1804-aarch64-install.run .
#COPY SentechSDK-1.0.5-Ubuntu1804-x86_64-install.run .
#COPY SentechSDK-1.1.2-Update5-Ubuntu1804-x86_64-install.run .
#COPY stapipy-1.1.2.1-cp37-cp37m-linux_x86_64.whl .
COPY stapipy-1.1.2.1-cp37-cp37m-linux_aarch64.whl .
RUN ./SentechSDK-1.1.2-Update5-Ubuntu1804-aarch64-install.run --accept -- "-y -p /opt/sentech"
#RUN ./SentechSDK-1.0.5-Ubuntu1804-x86_64-install.run --accept -- "-y -p /opt/sentech"
#RUN ./SentechSDK-1.1.2-Update5-Ubuntu1804-x86_64-install.run --accept -- "-y -p /opt/sentech"
RUN . /opt/sentech/.stprofile 
#RUN pip3 install stapipy-1.1.2.1-cp37-cp37m-linux_x86_64.whl
RUN pip3 install stapipy-1.1.2.1-cp37-cp37m-linux_aarch64.whl
RUN echo "source /opt/sentech/.stprofile" >> ~/.bashrc
RUN apt install -y nano
RUN apt install -y iproute2
RUN apt-get install -y iputils-ping
RUN pip3 install scikit-build
RUN pip3 install --upgrade pip
RUN pip3 install opencv-python
RUN rm -rf /var/lib/apt/lists/*


