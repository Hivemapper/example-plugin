import os
from flask import Flask, jsonify, request

app = Flask(__name__)

landmarks_data = [
    {"id": 595, "class_label": "speed-sign", "lat": 12.34, "lon": 56.78, "ts": 1744153669000 },
    {"id": 596, "class_label": "regulatory-speed-sign", "lat": 87.65, "lon": 43.21, "ts": 1744153670000 },
    {"id": 597, "class_label": "speed-sign", "lat": 11.11, "lon": 22.22, "ts": 1744153670000 },
    {"id": 598, "class_label": "speed-sign", "lat": 33.33, "lon": 44.44, "ts": 1744153671000 },
    {"id": 599, "class_label": "regulatory-speed-sign", "lat": 55.55, "lon": 66.66, "ts": 1744153672000 },
]

position_data = {
    "id":858894,
    "latitude":37.7880956,
    "longitude":-122.3992437,
    "altitude":-16.401,
    "estimated_speed":7.18377685546875,
    "utc_time":"2025-04-08 23:07:52.750329",
    "unix_timestamp": 1744153672750,
    "gdop":1.3900000000000001,
    "hdop":0.67,
    "eph":3.776,
}

position_context_data = [
  {
    "latitude": 37.6411744198726,
    "longitude": -122.405861053677,
    "altitude": -28.0009404761905,
    "speed": 28.7596985271999,
    "eph": 0.359
  },
  {
    "latitude": 37.6413001854137,
    "longitude": -122.405890111928,
    "altitude": -27.9415021459227,
    "speed": 28.8591388162114,
    "eph": 0.358763948497854
  },
]

info_data = {
    "ssid": "test_ssid",
    "api_version": "v1.0-test"
}

@app.route('/api/1/landmarks/latest', methods=['GET'])
def get_latest_landmark():
    if landmarks_data:
        return jsonify({
            "last_landmark": landmarks_data[-1],
            "last_observation": landmarks_data[-1]
        })
    return jsonify({})

@app.route('/api/1/landmarks/last/<int:n>', methods=['GET'])
def get_last_n_landmarks(n):
    last_n = landmarks_data[-n:] if n <= len(landmarks_data) else landmarks_data
    return jsonify(list(reversed(last_n)))

@app.route('/api/1/landmarks', methods=['GET'])
def get_landmarks():
    since = request.args.get('since', default=None, type=int)
    until = request.args.get('until', default=None, type=int)

    if since is None and until is None:
        return jsonify(landmarks_data)

    filtered = landmarks_data
    if since is not None:
        filtered = [lm for lm in filtered if lm["ts"] >= since]
    if until is not None:
        filtered = [lm for lm in filtered if lm["ts"] <= until]
    return jsonify(filtered)

@app.route('/api/1/landmarks/id/<int:id>', methods=['GET'])
def get_landmarks_after_id(id):
    filtered = [lm for lm in landmarks_data if lm["id"] >= id]
    return jsonify(filtered)

@app.route('/api/1/landmarks/positionContext/<int:n>', methods=['GET'])
def get_position_context(n):
    return jsonify(position_context_data)

@app.route('/api/1/info/', methods=['GET'])
def get_info():
    return jsonify(info_data)

@app.route('/api/1/gnssConcise/latestValid', methods=['GET'])
def get_latest_position():
    if position_data:
        return jsonify(position_data)
    return jsonify({})

@app.route('/api/1/gnssConcise/locationsBetweenUtcTime', methods=['GET'])
def get_positions_between_utc_time():
    if position_data:
        return jsonify(position_data)
    return jsonify({})

@app.route('/api/1/file/', methods=['POST'])
def upload_file():
    return jsonify({ "message": 'File created successfully.' }), 200

@app.route('/api/1/file/', methods=['DELETE'])
def delete_file():
    return jsonify({ "message": 'File created successfully.' }), 200

@app.route('/api/1/file/purge', methods=['GET'])
def purge_cache():
    return jsonify({ "message": 'Plugin cache directory purged successfully.' }), 200

@app.route('/api/1/file/exists/', methods=['GET'])
def file_exists():
    return jsonify({"exists": True})

@app.route('/api/1/file/list', methods=['GET'])
def list_files():
    return jsonify({"files": ["map1/map1.txt", "test.txt"]})


if __name__ == '__main__':
    host = os.environ.get('DASHCAM_HOST', '0.0.0.0')
    port = int(os.environ.get('DASHCAM_PORT', 5000))
    app.run(host=host, port=port)