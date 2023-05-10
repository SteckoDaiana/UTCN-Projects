import Header from "../components/User/UserHeader";
import UpdateUser from "../components/User/UpdateUser";
import LoginPage from "./Login";
function UpdateUserPage() {
  return (
    <>
      <Header heading="This is what you have to do to create an user !" />

      <div className=" flex justify-center  font-extrabold text-gray-900"></div>

      <UpdateUser />
    </>
  );
}
export default sessionStorage.getItem("admUID") ? UpdateUserPage : LoginPage;
