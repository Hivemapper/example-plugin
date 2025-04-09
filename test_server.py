import os
from flask import Flask, jsonify, request

app = Flask(__name__)

landmarks_data = [
    {"id": 595, "class_label": "Landmark A", "lat": 12.34, "lon": 56.78, "ts": 1744153669000 },
    {"id": 596, "class_label": "Landmark B", "lat": 87.65, "lon": 43.21, "ts": 1744153670000 },
    {"id": 597, "class_label": "Landmark C", "lat": 11.11, "lon": 22.22, "ts": 1744153670000 },
    {"id": 598, "class_label": "Landmark D", "lat": 33.33, "lon": 44.44, "ts": 1744153671000 },
    {"id": 599, "class_label": "Landmark E", "lat": 55.55, "lon": 66.66, "ts": 1744153672000 },
]

position_data = {
    "altitude":15.891,
    "cno":39,
    "heading":297.11066000000005,
    "id":858894,
    "latitude":37.7880956,
    "longitude":-122.3992437,
    "speed":0.029583653435111046,
    "utc_time":"2025-04-08 23:07:52.750329"
}

info_data = {
    "ssid": "test_ssid",
    "api_version": "v1.0-test"
}

@app.route('/api/1/landmarks/latest', methods=['GET'])
def get_latest_landmark():
    if landmarks_data:
        return jsonify(landmarks_data[-1])
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

@app.route('/api/1/landmarks/<int:id>', methods=['GET'])
def get_landmarks_after_id(id):
    filtered = [lm for lm in landmarks_data if lm["id"] >= id]
    return jsonify(filtered)

@app.route('/api/1/info/', methods=['GET'])
def get_info():
    return jsonify(info_data)

@app.route('/api/1/gnssConcise/latestValid', methods=['GET'])
def get_latest_position():
    if position_data:
        return jsonify(position_data)
    return jsonify({})

if __name__ == '__main__':
    host = os.environ.get('DASHCAM_HOST', '0.0.0.0')
    port = int(os.environ.get('DASHCAM_PORT', 5000))
    app.run(host=host, port=port)