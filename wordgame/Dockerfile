FROM --platform=linux/amd64 python:3.8-slim-buster
WORKDIR /app

# install dependencies
COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt

# copy over source
COPY . .

# run and expose
EXPOSE 3000
CMD ["python3", "-m" , "flask", "run", "--host=0.0.0.0", "--port=3000"]