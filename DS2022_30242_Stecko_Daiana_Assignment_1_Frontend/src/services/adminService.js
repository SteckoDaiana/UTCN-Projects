import axios from "axios";
const adminUrl = "http://localhost:8080/person";

class adminService {
  getPersons() {
    try {
      return axios.get(`${adminUrl}`);
    } catch {
      console.log("Error");
    }
  }
  insertProsumer(user) {
    try {
      return axios.post(`${adminUrl}`, user);
    } catch {
      console.log("Error");
    }
  }
  getPerson(id) {
    try {
      return axios.get(`${adminUrl}/${id}`);
    } catch {
      console.log("Error");
    }
  }
  deleteProsumer(id) {
    try {
      return axios.delete(`${adminUrl}/delete/${id}`);
    } catch {
      console.log("Error");
    }
  }
  updateProsumer(user) {
    try {
      return axios.post(`${adminUrl}/update`, user);
    } catch {
      console.log("Error");
    }
  }
}
export default new adminService();
