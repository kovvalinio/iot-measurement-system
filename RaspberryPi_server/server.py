import os
import json
from http.server import SimpleHTTPRequestHandler, HTTPServer

class CustomHTTPRequestHandler(SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/files':
            self.list_files()
        else:
            super().do_GET()

    def list_files(self):
        directory = './files'  
        try:
            file_list = os.listdir(directory)
            files = [{"name": f, "path": os.path.join(directory, f)} for f in file_list]
            response = json.dumps(files)


            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(response.encode())
        except OSError:
            self.send_error(404, "Katalog nie znaleziony")


def run(server_class=HTTPServer, handler_class=CustomHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Serwer HTTP działa na porcie 8000...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()
