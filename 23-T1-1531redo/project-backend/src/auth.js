import {getData, setData} from './dataStore.js'
import validator from 'validator';

/*
Given the email and password of a authUser, login that person, return the authUserId of the user.

Arguments:
    <email> (string)   - <email>
    <password> (string)   - <password>
Return Value:
    Returns <{ error: 'error' }> on <email entered does not belong to a user>
    Returns <{ error: 'error' }> on <password is not correct>
    Returns <{ authUserId }> on <can found user's email and password is correct>
*/

function authLoginV1(email, password){
    if (typeof email !== 'string' || typeof password !== 'string'){
        return {error: 'error'};
    }
    const obj = getData();
    for (let i of obj.user){
        if (i.email === email && i.password === password){
            if (obj.globalFirst) {
                i.permission = 1;
                obj.globalFirst = false;
                setData(obj);
            }
            return {authUserId: i.uId};
        }
        else if (i.email === email && i.password !== password){
            return {error: 'error'};
        }
    }
    return {error: 'error'};
}

function name_is_taken(name, data_obj){
    for (let i of data_obj.user){
        if (i.handleNameStr === name){
            return true;
        }
    }
    return false;
}

function email_is_taken(email, data_obj){
    for (let i of data_obj.user){
        if (i.email === email){
            return true;
        }
    }
    return false;
}

function handle_names(first_name, last_name, data_obj){
    let name = first_name + last_name;
    name = name.toLowerCase()
    name = name.replace(/[^a-z0-9]/g,'');
    if (name.length > 20){
        name = name.slice(0, 20);
    }
    let original_length = name.length;
    for(let i = 0; name_is_taken(name,data_obj);i++){
        if (i === 0){
            name += i.toString();
            continue;
        }
        name = name.slice(0, original_length);
        name += i.toString();
    }
    return name;
}

function is_valid_register_input(email, password, nameFirst, nameLast, data_obj){
    if((validator.isEmail(email)) === false){
        return false;
    }
    else if (email_is_taken(email, data_obj)){
        return false;
    }
    else if (password.length < 6){
        return false;
    }
    else if (!(nameFirst.length >= 1 && nameFirst.length <= 50)){
        return false;
    }
    else if (!(nameLast.length >= 1 && nameLast.length <= 50)){
        return false;
    }
    return true;
}

/*
Given the email, password, nameFirst and nameLast of a User,
create a new account and register that person, return the authUserId of that registered user if succeed.

Arguments:
    <email> (string)   - <email>
    <password> (string)   - <password>
    <nameFirst> (string)   - <string>
    <nameLast> (string)   - <string>
Return Value:
    Returns <{ error: 'error' }> on <email entered is not a valid email>
    Returns <{ error: 'error' }> on <email address is already being used by another user>
    Returns <{ error: 'error' }> on <length of password is less than 6 characters>
    Returns <{ error: 'error' }> on <length of nameFirst or nameLast is not between 1 and 50 characters inclusive>
    Returns <{ authUserId }> on <successfully create and registered that person>
*/
function authRegisterV1(email, password, nameFirst, nameLast){
    if (typeof email !== 'string' || typeof password !== 'string' || typeof nameFirst !== 'string' || typeof nameLast !== 'string'){
        return {error: 'error'};
    }
    let obj = getData();
    if (is_valid_register_input (email, password, nameFirst, nameLast, obj) === false){
        return {error: 'error'};
    }
    const valid_name = handle_names(nameFirst, nameLast, obj);
    const authUserId = obj.user.length + 5201314;
    const new_user = {
        'uId' : authUserId,
        'email' : email,
        'password' : password,
        'handleNameStr' : valid_name,    //Combined handle name str of first name and last name
        'nameFirst' : nameFirst,
        'nameLast' : nameLast,
        'permission' : 2,
    }
    obj.user.push(new_user);
    setData(obj);
    return {authUserId: authUserId};
}
export {authLoginV1, authRegisterV1}
