FROM python:3.11-slim-bullseye
WORKDIR /app

# Install dependencies
COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt

# Copy over everything else
COPY . .

# Run the server!
EXPOSE 3000
CMD [ "python3", "./server.py"]