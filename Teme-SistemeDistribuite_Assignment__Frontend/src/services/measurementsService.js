import axios from "axios";
const adminUrl = "http://localhost:8080/measurements";

class measurementsService {
  getMeasurements() {
    try {
      return axios.get(`${adminUrl}`);
    } catch {
      console.log("Error");
    }
  }
  insertMeasurements(item) {
    try {
      return axios.post(`${adminUrl}`, item);
    } catch {
      console.log("Error");
    }
  }
  getMeasurementsById(id_mes) {
    try {
      return axios.get(`${adminUrl}/${id_mes}`);
    } catch {
      console.log("Error");
    }
  }
  deleteDevice(id_device) {
    try {
      return axios.delete(`${adminUrl}/delete/${id_device}`);
    } catch {
      console.log("Error");
    }
  }
  updateDevice(item) {
    try {
      return axios.post(`${adminUrl}/updateMes`, item);
    } catch {
      console.log("Error");
    }
  }
}
export default new measurementsService();
