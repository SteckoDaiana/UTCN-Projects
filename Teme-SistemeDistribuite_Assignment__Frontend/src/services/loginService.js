import axios from "axios";
const adminUrl = "http://localhost:8080/person";

class loginService {
  userLogin(user) {
    try {
      const userCredentials = {
        username: user.eusername,
        password: user.password,
      };
      return axios.post(`${adminUrl}/userLogin`, userCredentials);
    } catch {
      console.log("Error");
    }
  }
}
export default new loginService();
