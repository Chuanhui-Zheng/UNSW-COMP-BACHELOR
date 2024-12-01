import { getData, setData } from './dataStore.js'
import { authLoginV1, authRegisterV1 } from './auth.js'
import validator from 'validator';

function isValidName(name) {
    if (name.length < 1) {
        return false;
    }
    if (name.length > 20) {
        return false;
    }
    return true;
}

function authInvalid(authUserId, data_obj) {
    for (let i of data_obj) {
        if (i.uId === authUserId) {
            return true;
        }
    }
    return false;
}

const get_user_from_obj =(userId) =>{
    const data = getData();
    for(let i of data.user){
        if(i.uId === userId){
            return i;
        }
    }
    return null;
}

/*

function channelsCreateV1(authUserId, name, isPublic) {
    let obj = getData();
    if (isValidName(name) === false) {
        return { error: 'error' };
    }
    if (authInvalid(authUserId, obj.user) === false) {
        return { error: 'error' };
    }
    const channelId = obj.channels.length + 0;
    const ownerMembers = [];
    const allMembers = [];
    ownerMembers.push(get_user_from_obj(authUserId));
    allMembers.push(get_user_from_obj(authUserId));
    const newChannel = {
        'name': name,
        'channelId': channelId,
        'isPublic': isPublic,
        'ownerMembers': ownerMembers,
        'allMembers' : allMembers,
        'messages' : [],
    }
    obj.channels.push(newChannel);
    setData(obj);
    return {channelId:channelId};
}
*/

function channelsCreateV1(authUserId, name, isPublic) {
    let obj = getData();
    if (isValidName(name) === false) {
        return { error: 'error' };
    }
    if (authInvalid(authUserId, obj.user) === false) {
        return { error: 'error' };
    }
    const channelId = obj.channels.length;
    const ownerMembers = [];
    const allMembers = [];
    ownerMembers.push(get_user_from_obj(authUserId));
    allMembers.push(get_user_from_obj(authUserId));
    const newChannel = {
        'name': name,
        'channelId': channelId,
        'isPublic': isPublic,
        'ownerMembers': ownerMembers,
        'allMembers' : allMembers,
        'messages' : [],
    }
    obj.channels.push(newChannel);
    setData(obj);
    return {channelId:channelId};
}

/*
Find the channel containing the user based on the id entered by the user

Arguments:
    <authUserId> (int)   - <User Id>
Return Value:
    Returns <{ error: 'error' }> on <auth can not found>
    Returns <{ channels }> on <can found user channels>
 */
function channelsListV1(authUserId) {
    let obj = getData();
    if (authInvalid(authUserId, obj.user) === false) {
        return { error: 'error' };//?
    }
    let channel_list = [];
    for (let i of obj.channels) {
        for (let item of i.allMembers) {
            if (item.uId === authUserId) {
                channel_list.push({
                    channelId: i.channelId,
                    name: i.name,
                });
                break;
            }
        }

    }
    return { channels: channel_list};
}
    

function channelsListallV1(authUserId){
    if (typeof authUserId != 'number') return {error: 'error'};
    if (authUserId < 0) return {error: 'error'};
    let store = getData();
    if (store.user.findIndex(i => i.uId === authUserId) === -1) return {error: 'error'};
    // return all channels {channelId, name}
    let channel_data_store = store.channels;
     let channel_list = [];
     for (let i = 0; i < channel_data_store.length; i++) {
         channel_list.push({
             channelId: channel_data_store[i].channelId,
             name: channel_data_store[i].name,
         });
     }
    return {channels: channel_list};
}



export { channelsCreateV1, channelsListV1, channelsListallV1}
