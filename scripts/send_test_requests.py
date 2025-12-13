#!/usr/bin/env python3
"""
Quick smoke sender for the temp print server.
Requires python -m pip install grpcio grpcio-tools.
"""
import subprocess
import sys
import tempfile
from pathlib import Path
import grpc


def generate_stubs(proto_root: Path, out_dir: Path):
    protos = [
        "v1/primitives/bool.proto",
        "v1/primitives/int.proto",
        "v1/primitives/string.proto",
        "v1/collections/list.proto",
        "v1/collections/common.proto",
        "v1/collections/element_kind.proto",
    ]
    args = [
        sys.executable,
        "-m",
        "grpc_tools.protoc",
        f"-I{proto_root}",
        f"--python_out={out_dir}",
        f"--grpc_python_out={out_dir}",
    ] + protos
    subprocess.check_call(args, cwd=proto_root)


def main():
    repo_root = Path(__file__).resolve().parent.parent
    proto_root = repo_root / "proto"
    with tempfile.TemporaryDirectory() as td:
        out_dir = Path(td)
        generate_stubs(proto_root, out_dir)
        sys.path.insert(0, str(out_dir))

        from v1.primitives import bool_pb2_grpc as bool_grpc, bool_pb2
        from v1.primitives import int_pb2_grpc as int_grpc, int_pb2
        from v1.primitives import string_pb2_grpc as str_grpc, string_pb2
        from v1.collections import list_pb2_grpc as list_grpc, list_pb2

        channel = grpc.insecure_channel("localhost:50051")

        bool_stub = bool_grpc.BoolCacheServiceStub(channel)
        int_stub = int_grpc.IntCacheServiceStub(channel)
        str_stub = str_grpc.StringCacheServiceStub(channel)
        list_stub = list_grpc.ListCacheServiceStub(channel)

        print("Sending Bool Set")
        bool_stub.Set(bool_pb2.BoolSetRequest(id="b1", value=True))

        print("Sending Int Set/Get/Delete")
        int_stub.Set(int_pb2.IntSetRequest(id="i1", value=42))
        int_resp = int_stub.Get(int_pb2.IntGetRequest(id="i1"))
        print("Int get response:", int_resp.value)
        int_stub.Delete(int_pb2.IntDeleteRequest(id="i1"))

        print("Sending String Set")
        str_stub.Set(string_pb2.StringSetRequest(id="s1", value="hello"))

        print("Sending List Set")
        list_stub.Set(list_pb2.ListSetRequest(id="l1", elements=[]))

        print("Done. Check server stdout for printed messages.")


if __name__ == "__main__":
    main()
