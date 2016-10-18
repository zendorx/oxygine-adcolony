#include <jni.h>
#include <android/log.h>
#include <assert.h>
#include "core/oxygine.h"
#include "core/Object.h"
#include "core/ThreadMessages.h"
#include "core/oxygine.h"
#include "core/android/jniHelper.h"
#include "core/android/jniUtils.h"
#include "json/json.h"
#include "src/adcolony.h"


using namespace oxygine;

jclass _jAdcolonyClass = 0;
jobject _jAdcolonyObject = 0;

bool isAdcolonyEnabled()
{
    return _jAdcolonyClass && _jAdcolonyObject;
}


extern "C"
{
	JNIEXPORT void JNICALL Java_org_oxygine_adcolony_AdcolonyAdapter_onNativeChange(JNIEnv* env, jobject obj, int newStatus)
	{
		core::getMainThreadMessages().postCallback([ = ]()
		{
			onChangeStatus(newStatus);
		});
	}
	
    /*JNIEXPORT void JNICALL Java_org_oxygine_facebook_FacebookAdapter_newMeRequestResult(JNIEnv* env, jobject obj, jstring json_data, jboolean error)
    {
        string data = jniGetString(env, json_data);

        core::getMainThreadMessages().postCallback([ = ]()
        {
            facebook::internal::newMeRequestResult(data , (bool) error) ;
        });
    }

    JNIEXPORT void JNICALL Java_org_oxygine_facebook_FacebookAdapter_newToken(JNIEnv* env, jobject obj, jstring json_data)
    {
        string data = jniGetString(env, json_data);

        core::getMainThreadMessages().postCallback([ = ]()
        {
            facebook::internal::newToken(data) ;
        });
    }

    JNIEXPORT void JNICALL Java_org_oxygine_facebook_FacebookAdapter_loginResult(JNIEnv* env, jobject obj, jboolean value)
    {
        core::getMainThreadMessages().postCallback([ = ]()
        {
            facebook::internal::loginResult((bool) value) ;
        });
    }

    JNIEXPORT void JNICALL Java_org_oxygine_facebook_FacebookAdapter_newMyFriendsRequestResult(JNIEnv* env, jobject obj, jstring json_data, jboolean error)
    {
        string data = jniGetString(env, json_data);

        core::getMainThreadMessages().postCallback([ = ]()
        {
            facebook::internal::newMyFriendsRequestResult(data, (bool) error);
        });
    }*/
}

bool jniAdcolonyIsLoaded()
{
	if (!isAdcolonyEnabled())
        return false;

    bool result = false;
    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jisloaded = env->GetMethodID(_jAdcolonyClass, "isLoggedIn", "()Z");
        JNI_NOT_NULL(jisloaded);

        jboolean jb = env->CallBooleanMethod(_jAdcolonyObject, jisloaded);
        result = (bool) jb;

    }
    catch (const notFound&)
    {
        log::error("jniAdcolonyIsLoaded failed, class/member not found");
    }

    return result;
}

void jniAdcolonyLoad()
{
	if (!isAdcolonyEnabled())
	        return false;

	try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jmethod = env->GetMethodID(_jAdcolonyClass, "load", "()V");
        JNI_NOT_NULL(jmethod);

        env->CallVoidMethod(_jAdcolonyObject, jmethod);
    }
    catch (const notFound&)
    {
        log::error("jniAdcolonyLoad failed, class/member not found");
    }

}

void jniAdcolonyShow()
{
	if (!isAdcolonyEnabled())
	        return false;

	try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jmethod = env->GetMethodID(_jAdcolonyClass, "show", "()V");
        JNI_NOT_NULL(jmethod);

        env->CallVoidMethod(_jAdcolonyObject, jmethod);
    }
    catch (const notFound&)
    {
        log::error("jniAdcolonyShow failed, class/member not found");
    }
}


void onChangeStatus(int status)
{

}

void jniAdcolonyInit()
{
    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);
        JNI_NOT_NULL(env);

        _jAdcolonyClass = env->FindClass("org/oxygine/adcolony/AdcolonyAdapter");
        JNI_NOT_NULL(_jAdcolonyClass);

        _jAdcolonyClass = (jclass) env->NewGlobalRef(_jAdcolonyClass);
        JNI_NOT_NULL(_jAdcolonyClass);

        _jFacebookObject = env->NewGlobalRef(jniFindExtension(env, _jAdcolonyClass));
        JNI_NOT_NULL(_jAdcolonyObject);
    }
    catch (const notFound&)
    {
        log::error("jniAdcolonyInit failed, class/member not found");
    }
}

void jniAdcolonyFree()
{
    if (!isAdcolonyEnabled())
        return;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        env->DeleteGlobalRef(_jAdcolonyClass);
        _jAdcolonyClass = 0;

        env->DeleteGlobalRef(_jAdcolonyObject);
        _jAdcolonyObject = 0;
    }
    catch (const notFound&)
    {

    }
}

/*bool jniFacebookIsLoggedIn()
{
    if (!isFacebookEnabled())
        return false;

    bool result = false;
    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jisLoggedIn = env->GetMethodID(_jFacebookClass, "isLoggedIn", "()Z");
        JNI_NOT_NULL(jisLoggedIn);

        jboolean jb = env->CallBooleanMethod(_jFacebookObject, jisLoggedIn);
        result = (bool) jb;

    }
    catch (const notFound&)
    {
        log::error("jniFacebookIsLoggedIn failed, class/member not found");
    }

    return result;
}

void jniFacebookNewMeRequest()
{
    if (!isFacebookEnabled())
        return;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jnewMeRequest = env->GetMethodID(_jFacebookClass, "newMeRequest", "()V");
        JNI_NOT_NULL(jnewMeRequest);
        env->CallVoidMethod(_jFacebookObject, jnewMeRequest);

    }
    catch (const notFound&)
    {
        log::error("jniFacebookNewMeRequest failed, class/member not found");
    }
}

string jniFacebookGetAccessToken()
{
    if (!isFacebookEnabled())
        return "";

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jgetToken = env->GetMethodID(_jFacebookClass, "getAccessToken", "()Ljava/lang/String;");
        JNI_NOT_NULL(jgetToken);

        jobject obj = env->CallObjectMethod(_jFacebookObject, jgetToken);
        string data = jniGetString(env, (jstring) obj);
        return data;

    }
    catch (const notFound&)
    {
        log::error("jniFacebookGetAccessToken failed, class/member not found");
    }

    return "";
}

string jniFacebookGetUserID()
{
    if (!isFacebookEnabled())
        return "";

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jgetUserID = env->GetMethodID(_jFacebookClass, "getUserID", "()Ljava/lang/String;");
        JNI_NOT_NULL(jgetUserID);

        jobject obj = env->CallObjectMethod(_jFacebookObject, jgetUserID);
        string data = jniGetString(env, (jstring) obj);
        return data;

    }
    catch (const notFound&)
    {
        log::error("jniFacebookGetUserID failed, class/member not found");
    }

    return "";
}

bool jniFacebookAppInviteDialog(const string& appLinkUrl, const string& previewImageUrl)
{
    if (!isFacebookEnabled())
        return false;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jappInviteDialog = env->GetMethodID(_jFacebookClass, "appInviteDialog", "([Ljava/lang/String;[Ljava/lang/String;)Z");
        JNI_NOT_NULL(jappInviteDialog);

        jstring jappLinkUrl = env->NewStringUTF(appLinkUrl.c_str());
        jstring jpreviewImageUrl = env->NewStringUTF(previewImageUrl.c_str());

        env->CallVoidMethod(_jFacebookObject, jappInviteDialog, jappLinkUrl, jpreviewImageUrl);

    }
    catch (const notFound&)
    {
        log::error("jniFacebookGetFriends failed, class/member not found");
    }
}

void jniFacebookGetFriends()
{
    if (!isFacebookEnabled())
        return;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jgetFriends = env->GetMethodID(_jFacebookClass, "newMyFriendsRequest", "()V");
        JNI_NOT_NULL(jgetFriends);
        env->CallVoidMethod(_jFacebookObject, jgetFriends);

    }
    catch (const notFound&)
    {
        log::error("jniFacebookGetFriends failed, class/member not found");
    }

}
void jniFacebookLogin()
{
    if (!isFacebookEnabled())
        return;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jlogin = env->GetMethodID(_jFacebookClass, "login", "()V");
        JNI_NOT_NULL(jlogin);
        env->CallVoidMethod(_jFacebookObject, jlogin);

    }
    catch (const notFound&)
    {
        log::error("jniFacebookLogin failed, class/member not found");
    }
}*/