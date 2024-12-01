import {checkUserValid} from './users.js'
import {getData} from './dataStore.js'

///////////////////////////////////////////////////////////////////
/*               Channel join and invite helper function         */
function getUserById(authUserId) {
        // get the data storage
        let obj = getData();
        for (let user of obj.user) {
            // if the authUserId matches, return the current user
            if (user.uId === authUserId) {
                return user;
            }
        }
        return null;
    }
    
    function check_user_exist_in_channel(check_user_id, channel_members) {
        for (let user of channel_members) {
            if (user.uId === check_user_id) {
                return true;
            }
        }
        return false;
    }
    
    function check_Channel_exist_ById(channelId) {
        let obj = getData();
        for (let channel of obj.channels) {
            if (channel.channelId === channelId) {
                return true;
            }
        }
        return false;
    
    }
    
    function check_user_exist_ById(authUserId) {
        let obj = getData();
        for (let user of obj.user) {
            if (user.uId === authUserId) {
                return true;
            }
        }
        return false;
    }
    
    function getChannelById(channelId) {
        let obj = getData();
        for (let channel of obj.channels) {
            if (channel.channelId === channelId) {
                return channel;
            }
        }
        return null;
    
    }
//Helper
/////////////////////////////////////////////////////////////////////////// 

    function channelJoinV1(authUserId, channelId) {
        let channel_exit = check_Channel_exist_ById(channelId);
        if (channel_exit === false) {
            return {error: 'error'};
        }
        
        let channel = getChannelById(channelId);

        let user_exit = check_user_exist_in_channel(authUserId, channel.allMembers);
        if (user_exit === true) {
            return {error: 'error'};
        }

        //checking if channel is private, or authUser belongs to global owners
        if (!getData().channels[channelId].isPublic) {
            let users = getData().user;
            for (let u of users) {
                if (u.uId == authUserId && u.permission == 2) return {error: 'error'};
            }
        }

        channel.allMembers.push(getUserById(authUserId));
        return {};
    }
    
    function channelInviteV1(authUserId, channelId, uId) {
        let channel_exit = check_Channel_exist_ById(channelId);
        if (channel_exit === false) {
            return {error: 'error'};
        }
        let channel = getChannelById(channelId);
    
        let user_exit = check_user_exist_ById(authUserId);
        if (user_exit === false) {
            return {error: 'error'};
        }
        let user = getUserById(authUserId);
    
        let target_exit = check_user_exist_ById(uId);
        if (target_exit === false) {
            return {error: 'error'};
        }
        let target = getUserById(uId);
    
        let target_exit_in_channel = check_user_exist_in_channel(uId, channel.allMembers);
        if (target_exit_in_channel === true) {
            return {error: 'error'};
        }

        let user_exit_in_channel = check_user_exist_in_channel(authUserId, channel.allMembers);
        if (user_exit_in_channel === false) {
            return {error: 'error'};
        }
    
        channel.allMembers.push(target);
        return {};
    }
    

function channelDetailsV1 (authUserId, channelId) {
        let store = getData();
        // check if channelId is valid
        
        if (typeof channelId != 'number') return {error: 'error'};
        //console.log(store.channels);
        if (store.channels.findIndex(i => i.channelId === channelId) === -1) return {error: 'error'};

        // check if authUserId is valid
        if (typeof authUserId != 'number') return {error: 'error'};
        if (store.user.findIndex(i => i.uId === authUserId) === -1) return {error: 'error'};

        // check if user is in channel
        if (store.channels.find(i => i.channelId === channelId).allMembers.findIndex(i => i.uId === authUserId) === -1) return {error: 'error'};
        // return channel details { name, isPublic, ownerMembers, allMembers }
        let channel = store.channels.find(i => i.channelId === channelId);
        let the_result_owner_members = [];
        for (let i of channel.ownerMembers){
                const new_owner_member = {
                        uId : i.uId, 
                        email : i.email, 
                        nameFirst : i.nameFirst, 
                        nameLast : i.nameLast, 
                        handleStr : i.handleNameStr,
                };
                the_result_owner_members.push(new_owner_member); 
        }

        let the_result_all_members = [];
        for (let i of channel.allMembers){
                const new_all_member = {
                        uId : i.uId, 
                        email : i.email, 
                        nameFirst : i.nameFirst, 
                        nameLast : i.nameLast, 
                        handleStr : i.handleNameStr,
                };
                the_result_all_members.push(new_all_member); 
        }
        return {
                name: channel.name,
                isPublic: channel.isPublic,
                ownerMembers: the_result_owner_members,
                allMembers: the_result_all_members,
        };
}


function channelMessagesV1 (authUserId, channelId, start) {
        if (!checkUserValid(authUserId) || !checkChannelValid(channelId) || !checkMembership(authUserId, channelId)) return {error: 'error'};
        let data = getData().channels[channelId].messages;
        if (start > data.length || start < 0) return {error: 'error'};

        let messages = getData().messages;
        let end = (data.length > 50) ? (start + 50) : -1;
        let mess = [];
        for (let i of data) {
                mess.push(messages[messages.length - (i + 1)])
        }

        return {
                messages:  mess,
                start:  start,
                end:    end,
        };
}


//===Helpers===:
function checkChannelValid(channelId) {
        if (typeof channelId != 'number' || channelId < 0) return false;
        let data = getData().channels;
        return (data.findIndex(i => i.channelId == channelId) !== -1);
}

function checkMembership(authUserId, channelId) {
        let data = getData().channels;
        let cId = data.findIndex(i => i.channelId === channelId);
        return (data[cId].allMembers.findIndex(i => i.uId === authUserId) !== -1);
}

export {channelDetailsV1, channelJoinV1, channelInviteV1, channelMessagesV1,}
