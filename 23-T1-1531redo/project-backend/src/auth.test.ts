import request from 'sync-request';
import config from './config.json';

const PASS = 200;
const FAIL = 400;
const ERROR = {
    error: 'error',
};

describe('HTTP test authregister', () => {
    test('Test successfully register', () => {
        const regis = request(
        'POST',
            `${config.url}:${config.port}/auth/register/v2`,
            {
                json: {
                    "email" : 'nicetoseeyah@gmail.com', 
                    "password": 'hellomate',
                    "nameFirst" : 'blabla',
                    "nameLast" : 'blabla'
                }
            }
        );
        const register_details = JSON.parse(regis.getBody() as string);
        expect(regis.statusCode).toBe(PASS);
        expect(register_details.token).toStrictEqual(expect.any(String));
        expect(register_details.authUserId ).toStrictEqual(expect.any(Number));
    });

    test('Test invalid email address', () => {
        const test_regis1 = request(
            'POST',
            `${config.url}:${config.port}/auth/register/v2`,
            {
                json: {
                    "email" : 'nicetoseeyah@hey.tts', 
                    "password": 'ello',
                    "nameFirst" : 'blabla',
                    "nameLast" : 'blabla'
                }
            }
        );
        const register_details1 = JSON.parse(test_regis1.getBody() as string);
        expect(test_regis1.statusCode).toBe(FAIL);
        expect(register_details1.token).toStrictEqual(ERROR);
        expect(register_details1.authUserId ).toStrictEqual(ERROR);
    });

    test('Test email address already been used', () => {
        const test_regis2 = request(
            'POST',
            `${config.url}:${config.port}/auth/register/v2`,
            {
                json: {
                    "email" : 'nicetoseeyah@gmail.com', 
                    "password": 'hellomate',
                    "nameFirst" : 'blabla',
                    "nameLast" : 'blabla'
                }
            }
        );
        const register_details2 = JSON.parse(test_regis2.getBody() as string);
        expect(test_regis2.statusCode).toBe(FAIL);
        expect(register_details2.token).toStrictEqual(ERROR);
        expect(register_details2.authUserId ).toStrictEqual(ERROR);
    });

    clearV1();

    test('Test length of password less than 6 characters', () => {
        const test_regis3 = request(
            'POST',
            `${config.url}:${config.port}/auth/register/v2`,
            {
                json: {
                    "email" : 'nicetoseeyah@gmail.com', 
                    "password": 'hello',
                    "nameFirst" : 'blabla',
                    "nameLast" : 'blabla'
                }
            }
        );
        const register_details3 = JSON.parse(test_regis3.getBody() as string);
        expect(test_regis3.statusCode).toBe(FAIL);
        expect(register_details3.token).toStrictEqual(ERROR);
        expect(register_details3.authUserId ).toStrictEqual(ERROR);
    });

    clearV1();

    test('Test length of nameFirst is not between 1 and 50 characters inclusive', () => {
        const test_regis4 = request(
            'POST',
            `${config.url}:${config.port}/auth/register/v2`,
            {
                json: {
                    "email" : 'nicetoseeyah@gmail.com', 
                    "password": 'hellomate',
                    "nameFirst" : '',
                    "nameLast" : 'blabla'
                }
            }
        );
        const register_details4 = JSON.parse(test_regis4.getBody() as string);
        expect(test_regis4.statusCode).toBe(FAIL);
        expect(register_details4.token).toStrictEqual(ERROR);
        expect(register_details4.authUserId ).toStrictEqual(ERROR);
    });
    
    clearV1();

    test('Test length of nameLast is not between 1 and 50 characters inclusive', () => {
        const test_regis5 = request(
            'POST',
            `${config.url}:${config.port}/auth/register/v2`,
            {
                json: {
                    "email" : 'nicetoseeyah@gmail.com', 
                    "password": 'hellomate',
                    "nameFirst" : 'blabla',
                    "nameLast" : ''
                }
            }
        );
        const register_details5 = JSON.parse(test_regis5.getBody() as string);
        expect(test_regis5.statusCode).toBe(FAIL);
        expect(register_details5.token).toStrictEqual(ERROR);
        expect(register_details5.authUserId ).toStrictEqual(ERROR);
    });
});

describe('HTTP test authlogin', () => {
    test('Test successful login', () => {
        const login = request(
          'POST',
                `${config.url}:${config.port}/auth/login/v2`,
                {
                    json: {
                        "email" : 'nicetoseeyah@gmail.com', 
                        "password": 'hellomate',
                    }
                }
        );
        const loginsuccess = JSON.parse(login.getBody() as string);
        expect(login.statusCode).toBe(PASS);
        expect(loginsuccess.token).toStrictEqual(expect.any(String));
        expect(loginsuccess.authUserId ).toStrictEqual(expect.any(Number));
    }); 

    test('Test email entered does not belong to a user', () => {
        const test_login1 = request(
          'POST',
                `${config.url}:${config.port}/auth/login/v2`,
                {
                    json: {
                        "email" : 'WrongEmailAddress@gmail.com', 
                        "password": 'hellomate',
                    }
                }
        );
        const login_details1 = JSON.parse(test_login1.getBody() as string);
        expect(test_login1.statusCode).toBe(FAIL);
        expect(login_details1.token).toStrictEqual(ERROR);
        expect(login_details1.authUserId ).toStrictEqual(ERROR);
    }); 

    test('Test password is not correct', () => {
        const test_login2 = request(
          'POST',
                `${config.url}:${config.port}/auth/login/v2`,
                {
                    json: {
                        "email" : 'nicetoseeyah@gmail.com', 
                        "password": 'WrongPassword',
                    }
                }
        );
        const login_details2 = JSON.parse(test_login2.getBody() as string);
        expect(test_login2.statusCode).toBe(FAIL);
        expect(login_details2.token).toStrictEqual(ERROR);
        expect(login_details2.authUserId ).toStrictEqual(ERROR);
    }); 
});