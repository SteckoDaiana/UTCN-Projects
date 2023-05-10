import axios from "axios";
const adminUrl = "http://localhost:8080/device";

class deviceService {
  getItems() {
    try {
      return axios.get(`${adminUrl}`);
    } catch {
      console.log("Error");
    }
  }
  insertItem(item) {
    try {
      return axios.post(`${adminUrl}`, item);
    } catch {
      console.log("Error");
    }
  }
  getItem(id_item) {
    try {
      return axios.get(`${adminUrl}/${id_item}`);
    } catch {
      console.log("Error");
    }
  }
  deleteItem(id_item) {
    try {
      return axios.delete(`${adminUrl}/delete/${id_item}`);
    } catch {
      console.log("Error");
    }
  }
  updateProsumer(item) {
    try {
      return axios.post(`${adminUrl}/updateItem`, item);
    } catch {
      console.log("Error");
    }
  }
}
export default new deviceService();
