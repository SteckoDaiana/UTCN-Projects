import { useEffect, useState } from "react";
import { loginFields } from "../../constants/formFields";
import FormAction from "../FormAction";
import Input from "../Input";
import loginService from "../../services/loginService";
import LoginPage from "../../pages/Login";

const fields = loginFields;
let fieldsState = {};
fields.forEach((field) => (fieldsState[field.id] = ""));

export default function Login() {
  const [loginState, setLoginState] = useState(fieldsState);

  const handleChange = (e) => {
    setLoginState({ ...loginState, [e.target.id]: e.target.value });
  };
  const goToAdminPage = () => {
    window.location.href = "admin-page";
  };
  const goToClientPage = () => {
    window.location.href = "/client-page";
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    let res = authenticateUser().then((result) => {
      console.log(result.data.role === "CLIENT");
      if (result.data.role === "ADMINISTRATOR") {
        sessionStorage.setItem("admUID", result.data.id);
        sessionStorage.setItem("username", loginState.eusername);
        goToAdminPage();
      } else if (result.data.role === "CLIENT") {
        sessionStorage.setItem("clientUID", result.data.id);
        sessionStorage.setItem("username", loginState.eusername);
        goToClientPage();
      }
    });
  };

  const authenticateUser = async () => {
    return await loginService.userLogin(loginState);
  };

  useEffect(() => {
    console.log(loginState);
  }, [loginState]);
  return (
    <form className="mt-8 space-y-6" onSubmit={handleSubmit}>
      <div className="-space-y-px">
        {fields.map((field) => (
          <Input
            key={field.id}
            handleChange={handleChange}
            value={loginState[field.id]}
            labelText={field.labelText}
            labelFor={field.labelFor}
            id={field.id}
            name={field.name}
            type={field.type}
            isRequired={field.isRequired}
            placeholder={field.placeholder}
          />
        ))}
      </div>

      <FormAction handleSubmit={handleSubmit} text="Login" />
    </form>
  );
}
