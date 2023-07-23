FROM drogonframework/drogon:latest

WORKDIR /app
COPY . .
RUN mkdir build
RUN cd build && cmake .. && make

CMD ["./build/test/millie-api_test"]