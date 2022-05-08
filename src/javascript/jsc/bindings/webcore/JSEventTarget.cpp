/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSEventTarget.h"

#include "ActiveDOMObject.h"
#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "IDLTypes.h"
#include "JSAddEventListenerOptions.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructor.h"
#include "JSDOMConvertBase.h"
#include "JSDOMConvertBoolean.h"
#include "JSDOMConvertDictionary.h"
#include "JSDOMConvertEventListener.h"
#include "JSDOMConvertInterface.h"
#include "JSDOMConvertNullable.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMConvertUnion.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include "JSEvent.h"
#include "JSEventListener.h"
#include "JSEventListenerOptions.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSDestructibleObjectHeapCellType.h>
#include <JavaScriptCore/SlotVisitorMacros.h>
#include <JavaScriptCore/SubspaceInlines.h>
#include <variant>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>

namespace WebCore {
using namespace JSC;

// Functions

static JSC_DECLARE_HOST_FUNCTION(jsEventTargetPrototypeFunction_addEventListener);
static JSC_DECLARE_HOST_FUNCTION(jsEventTargetPrototypeFunction_removeEventListener);
static JSC_DECLARE_HOST_FUNCTION(jsEventTargetPrototypeFunction_dispatchEvent);

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsEventTargetConstructor);

class JSEventTargetPrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSEventTargetPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSEventTargetPrototype* ptr = new (NotNull, JSC::allocateCell<JSEventTargetPrototype>(vm)) JSEventTargetPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::GCClient::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSEventTargetPrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSEventTargetPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);

public:
    static constexpr unsigned StructureFlags = Base::StructureFlags | JSC::IsImmutablePrototypeExoticObject;
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSEventTargetPrototype, JSEventTargetPrototype::Base);

using JSEventTargetDOMConstructor = JSDOMConstructor<JSEventTarget>;

template<> EncodedJSValue JSC_HOST_CALL_ATTRIBUTES JSEventTargetDOMConstructor::construct(JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame)
{
    VM& vm = lexicalGlobalObject->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* castedThis = jsCast<JSEventTargetDOMConstructor*>(callFrame->jsCallee());
    ASSERT(castedThis);
    auto* context = castedThis->scriptExecutionContext();
    if (UNLIKELY(!context))
        return throwConstructorScriptExecutionContextUnavailableError(*lexicalGlobalObject, throwScope, "EventTarget");
    auto object = EventTarget::create(*context);
    if constexpr (IsExceptionOr<decltype(object)>)
        RETURN_IF_EXCEPTION(throwScope, {});
    static_assert(TypeOrExceptionOrUnderlyingType<decltype(object)>::isRef);
    auto jsValue = toJSNewlyCreated<IDLInterface<EventTarget>>(*lexicalGlobalObject, *castedThis->globalObject(), throwScope, WTFMove(object));
    if constexpr (IsExceptionOr<decltype(object)>)
        RETURN_IF_EXCEPTION(throwScope, {});
    setSubclassStructureIfNeeded<EventTarget>(lexicalGlobalObject, callFrame, asObject(jsValue));
    RETURN_IF_EXCEPTION(throwScope, {});
    return JSValue::encode(jsValue);
}
JSC_ANNOTATE_HOST_FUNCTION(JSEventTargetDOMConstructorConstruct, JSEventTargetDOMConstructor::construct);

template<> const ClassInfo JSEventTargetDOMConstructor::s_info = { "EventTarget"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSEventTargetDOMConstructor) };

template<> JSValue JSEventTargetDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSEventTargetDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "EventTarget"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSEventTarget::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSEventTargetPrototypeTableValues[] = {
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t) static_cast<PropertySlot::GetValueFunc>(jsEventTargetConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "addEventListener", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t) static_cast<RawNativeFunction>(jsEventTargetPrototypeFunction_addEventListener), (intptr_t)(2) } },
    { "removeEventListener", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t) static_cast<RawNativeFunction>(jsEventTargetPrototypeFunction_removeEventListener), (intptr_t)(2) } },
    { "dispatchEvent", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t) static_cast<RawNativeFunction>(jsEventTargetPrototypeFunction_dispatchEvent), (intptr_t)(1) } },
};

const ClassInfo JSEventTargetPrototype::s_info = { "EventTarget"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSEventTargetPrototype) };

void JSEventTargetPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSEventTarget::info(), JSEventTargetPrototypeTableValues, *this);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSEventTarget::s_info = { "EventTarget"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSEventTarget) };

JSEventTarget::JSEventTarget(Structure* structure, JSDOMGlobalObject& globalObject, Ref<EventTarget>&& impl)
    : JSDOMWrapper<EventTarget>(structure, globalObject, WTFMove(impl))
{
}

void JSEventTarget::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(info()));

    // static_assert(!std::is_base_of<ActiveDOMObject, EventTarget>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");
}

JSObject* JSEventTarget::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSEventTargetPrototype::create(vm, &globalObject, JSEventTargetPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSEventTarget::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSEventTarget>(vm, globalObject);
}

JSValue JSEventTarget::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSEventTargetDOMConstructor, DOMConstructorID::EventTarget>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSEventTarget::destroy(JSC::JSCell* cell)
{
    JSEventTarget* thisObject = static_cast<JSEventTarget*>(cell);
    thisObject->JSEventTarget::~JSEventTarget();
}

JSC_DEFINE_CUSTOM_GETTER(jsEventTargetConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSEventTargetPrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSEventTarget::getConstructor(JSC::getVM(lexicalGlobalObject), prototype->globalObject()));
}

static inline JSC::EncodedJSValue jsEventTargetPrototypeFunction_addEventListenerBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSEventTarget>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->wrapped();
    if (UNLIKELY(callFrame->argumentCount() < 2))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto type = convert<IDLAtomStringAdaptor<IDLDOMString>>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    EnsureStillAliveScope argument1 = callFrame->uncheckedArgument(1);
    auto listener = convert<IDLNullable<IDLEventListener<JSEventListener>>>(*lexicalGlobalObject, argument1.value(), *castedThis, [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwArgumentMustBeObjectError(lexicalGlobalObject, scope, 1, "listener", "EventTarget", "addEventListener"); });
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    EnsureStillAliveScope argument2 = callFrame->argument(2);
    auto options = argument2.value().isUndefined() ? false : convert<IDLUnion<IDLDictionary<AddEventListenerOptions>, IDLBoolean>>(*lexicalGlobalObject, argument2.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    auto result = JSValue::encode(toJS<IDLUndefined>(*lexicalGlobalObject, throwScope, [&]() -> decltype(auto) { return impl.addEventListenerForBindings(WTFMove(type), WTFMove(listener), WTFMove(options)); }));
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    vm.writeBarrier(&static_cast<JSObject&>(*castedThis), argument1.value());
    return result;
}

JSC_DEFINE_HOST_FUNCTION(jsEventTargetPrototypeFunction_addEventListener, (JSGlobalObject * lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSEventTarget>::call<jsEventTargetPrototypeFunction_addEventListenerBody>(*lexicalGlobalObject, *callFrame, "addEventListener");
}

static inline JSC::EncodedJSValue jsEventTargetPrototypeFunction_removeEventListenerBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSEventTarget>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->wrapped();
    if (UNLIKELY(callFrame->argumentCount() < 2))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto type = convert<IDLAtomStringAdaptor<IDLDOMString>>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    EnsureStillAliveScope argument1 = callFrame->uncheckedArgument(1);
    auto listener = convert<IDLNullable<IDLEventListener<JSEventListener>>>(*lexicalGlobalObject, argument1.value(), *castedThis, [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwArgumentMustBeObjectError(lexicalGlobalObject, scope, 1, "listener", "EventTarget", "removeEventListener"); });
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    EnsureStillAliveScope argument2 = callFrame->argument(2);
    auto options = argument2.value().isUndefined() ? false : convert<IDLUnion<IDLDictionary<EventListenerOptions>, IDLBoolean>>(*lexicalGlobalObject, argument2.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    auto result = JSValue::encode(toJS<IDLUndefined>(*lexicalGlobalObject, throwScope, [&]() -> decltype(auto) { return impl.removeEventListenerForBindings(WTFMove(type), WTFMove(listener), WTFMove(options)); }));
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    vm.writeBarrier(&static_cast<JSObject&>(*castedThis), argument1.value());
    return result;
}

JSC_DEFINE_HOST_FUNCTION(jsEventTargetPrototypeFunction_removeEventListener, (JSGlobalObject * lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSEventTarget>::call<jsEventTargetPrototypeFunction_removeEventListenerBody>(*lexicalGlobalObject, *callFrame, "removeEventListener");
}

static inline JSC::EncodedJSValue jsEventTargetPrototypeFunction_dispatchEventBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSEventTarget>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->wrapped();
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto event = convert<IDLInterface<Event>>(*lexicalGlobalObject, argument0.value(), [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwArgumentTypeError(lexicalGlobalObject, scope, 0, "event", "EventTarget", "dispatchEvent", "Event"); });
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLBoolean>(*lexicalGlobalObject, throwScope, impl.dispatchEventForBindings(*event))));
}

JSC_DEFINE_HOST_FUNCTION(jsEventTargetPrototypeFunction_dispatchEvent, (JSGlobalObject * lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSEventTarget>::call<jsEventTargetPrototypeFunction_dispatchEventBody>(*lexicalGlobalObject, *callFrame, "dispatchEvent");
}

JSC::GCClient::IsoSubspace* JSEventTarget::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<JSEventTarget, UseCustomHeapCellType::No>(
        vm,
        [](auto& spaces) { return spaces.m_clientSubspaceForEventTarget.get(); },
        [](auto& spaces, auto&& space) { spaces.m_clientSubspaceForEventTarget = WTFMove(space); },
        [](auto& spaces) { return spaces.m_subspaceForEventTarget.get(); },
        [](auto& spaces, auto&& space) { spaces.m_subspaceForEventTarget = WTFMove(space); });
}

template<typename Visitor>
void JSEventTarget::visitChildrenImpl(JSCell* cell, Visitor& visitor)
{
    auto* thisObject = jsCast<JSEventTarget*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    Base::visitChildren(thisObject, visitor);
    thisObject->visitAdditionalChildren(visitor);
}

DEFINE_VISIT_CHILDREN(JSEventTarget);

template<typename Visitor>
void JSEventTarget::visitOutputConstraints(JSCell* cell, Visitor& visitor)
{
    auto* thisObject = jsCast<JSEventTarget*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    Base::visitOutputConstraints(thisObject, visitor);
    thisObject->visitAdditionalChildren(visitor);
}

template void JSEventTarget::visitOutputConstraints(JSCell*, AbstractSlotVisitor&);
template void JSEventTarget::visitOutputConstraints(JSCell*, SlotVisitor&);
void JSEventTarget::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSEventTarget*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSEventTargetOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, const char** reason)
{
    auto* jsEventTarget = jsCast<JSEventTarget*>(handle.slot()->asCell());
    if (jsEventTarget->wrapped().isFiringEventListeners()) {
        if (UNLIKELY(reason))
            *reason = "EventTarget firing event listeners";
        return true;
    }
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSEventTargetOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsEventTarget = static_cast<JSEventTarget*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsEventTarget->wrapped(), jsEventTarget);
}

}
