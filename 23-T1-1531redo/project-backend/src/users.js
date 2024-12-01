import {getData} from './dataStore.js'

function userProfileV1(authUserId, uId) {
  if (!checkUserValid(authUserId)) return {error: 'error'};
  let data = getData().user;
  for (let u of data) {
    if (u.uId == uId) 
    {
      return {
        user: {
          uId : u.uId,
          email : u.email,
          nameFirst : u.nameFirst, 
          nameLast : u.nameLast, 
          handleStr : u.handleNameStr,
        }
      };
    }
  }
  return {error: 'error'};
}

//===Helpers===:

function checkUserValid(uId) {
  if (typeof uId != 'number' || uId < 0) return false;
  let data = getData().user;
  for (let u of data) {
    if (u.uId == uId) return true;
  }
  return false;
}

export { userProfileV1, checkUserValid }
