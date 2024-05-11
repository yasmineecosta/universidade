import socket, socketserver
import threading
import time
import os
import uuid
import json
from base64 import b64encode, b64decode
from peer import Peer
from datetime import datetime


class Application:
    def __init__(self):
        self.peers = []
        self.peer_id = str(uuid.uuid4())
        self.address = '
