FROM --platform=linux/amd64 python:3.8-slim-buster

RUN useradd -m -d /home/ctf -u 12345 ctf
WORKDIR /home/ctf

# install dependencies
COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt


# copy over source
COPY . .
# restrict it
RUN chown -R root:root /home/ctf
RUN chmod +x ynetd


# run and expose
USER ctf
EXPOSE 9999
# CMD ["sh"]
CMD ["./ynetd", "-p", "9999", "python3 signature-i.py"]